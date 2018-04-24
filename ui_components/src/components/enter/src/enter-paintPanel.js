/**
 * Paint panel.
 */
EnterComponent.PaintPanel = function (containerId) {
	this.containerId = containerId;
};

EnterComponent.PaintPanel.prototype = {

	init: function () {
		this._initMarkup(this.containerId);
	},

	_initMarkup: function (containerId) {
		var container = $('#' + containerId);
		var self = this;

		container.append('<div class="sc-no-default-cmd">Ввод данных:</div>');
		
		container.append(
			'<form>' +
				'<label for="element-search-input">Выберите элемент: </label>' + 
				'<div id="search-panel">' + 
					'<form role="search">' + 
						'<div class="form-group">' + 
							'<input id="element-search-input" type="text" class="typeahead form-control" x-webkit-speech sc_control_sys_idtf="ui_control_search_idtf_edit" style="width: 250px;" data-provide="typeahead" autocomplete="off">' + 
							'<input type="hidden" id="sysId" value="">' + 
						'</div>' + 
					'</form>' + 
				'</div>' + 
				'<label for="mass">Введите массу (в граммах):</label>' + 
				'<input type="text" id="mass" name="mass" pattern="\d+([\.,]\d+)?">' + 
				'<button id="find" type="button">Найти химическое количество</button>' + 
			'</form>'
		);

		$('#element-search-input.typeahead').typeahead({
				minLength: 3,
				highlight: true,
			},
			{
				name: 'idtf',
				source: function (query, cb) {
					$('#element-search-input').addClass('search-processing');
					SCWeb.core.Server.findIdentifiersSubStr(query, function (data) {
						keys = [];

						var addValues = function (key) {
							var list = data[key];
							if (list) {
								for (idx in list) {
									var value = list[idx]
									keys.push({name: value[1], addr: value[0], group: key});
								}
							}
						}

						addValues('sys');
						addValues('main');
						addValues('common');

						cb(keys);
						$('#element-search-input').removeClass('search-processing');
					});
				},
				displayKey: 'name',
				templates: {
					suggestion: function (item) {
						var html = '';
						if (item.group === 'common') {
							return '<p class="sc-content">' + item.name + '</p>';
						} else {
							var cl = 'glyphicon glyphicon-user';
							if (item.group === 'sys') {
								cl = 'glyphicon glyphicon-globe';
							}
							return '<p><span class="tt-suggestion-icon ' + cl + '"></span>' + item.name + '</p>';
						}
						return '<p>' + item.name + '</p>';
					}
				}
			}
		).bind('typeahead:selected', function (evt, item, dataset) {
			if (item && item.addr) {
				$('#sysId').val([item.addr])
			}
		});
		
		$('#find').click(function () {
			var element = $("#sysId").val();
			console.log('element',element);
			var mass = $("#mass").val();
			console.log('mass',mass);
			self._createElement(element, mass);
		});
	},

	_findChemicalAmount: function (system_idtf) {
		SCWeb.core.Server.resolveScAddr(["ui_menu_find_chemical_amount_of_substance"],
		function (data) {
			var cmd = data["ui_menu_find_chemical_amount_of_substance"];
			SCWeb.core.Main.doCommand(cmd, [system_idtf], function (result) {
				if (result.question != undefined) {
					SCWeb.ui.WindowManager.appendHistoryItem(result.question);
				}
			});
		});
	},

	_createElement: function (el, m) {
		console.log('creating element');
		var self = this;
		var element = parseInt(el);

		window.sctpClient.create_node(sc_type_const).done(function (elementExample) {
			console.log('create node eleme example:',elementExample);
			window.sctpClient.create_link().done(function (linkName) {
				console.log('create link:',linkName);
				window.sctpClient.set_link_content(linkName, 'example_' + el);
				window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, elementExample, linkName).done(function (commonArcOne) {
					console.log('create arc:',commonArcOne);
					window.sctpClient.create_arc(sc_type_arc_pos_const_perm, window.scKeynodes.nrel_system_identifier, commonArcOne);
					window.sctpClient.create_arc(sc_type_arc_pos_const_perm, element, elementExample);
					self._createValue(elementExample, m);
				});
			});
		});
	},

	_createValue: function(elementExample, m) {
		console.log('creating value');
		var self = this;

		SCWeb.core.Server.resolveScAddr(['value', 'nrel_mass', 'lang_ru'], function (keynodes) {
			var nrelMass = keynodes['nrel_mass'];
			var value = keynodes['value'];
			var lang = keynodes['lang_ru'];

			window.sctpClient.create_node(sc_type_const).done(function (val) {
				console.log('create node val:',val);
				window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, elementExample, val).done(function (commonArcTwo) {
					window.sctpClient.create_arc(sc_type_arc_pos_const_perm, nrelMass, commonArcTwo);
					window.sctpClient.create_arc(sc_type_arc_pos_const_perm, value, val);
					self._createMeasurement(val, m, elementExample);
				});
			});
		});
	},

	_createMeasurement: function (val, m, elementExample) {
		console.log('creating measurements');
		var self = this;    	

		SCWeb.core.Server.resolveScAddr(['nrel_measurement'], function (keynodes) {
			var nrelMeasurement = keynodes['nrel_measurement'];

			window.sctpClient.create_node(sc_type_const).done(function (meas) {
				console.log('create node meas:',meas);
				window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, meas, val).done(function (commonArcThree) {
					window.sctpClient.create_arc(sc_type_arc_pos_const_perm, nrelMeasurement, commonArcThree);
					SCWeb.core.Server.resolveScAddr([m], function (key) {
						var addr = key[m];
						if (addr != undefined) {
							console.log('addr exist');
							self._createGramMeasurement(meas, addr, elementExample);
						} else {
							console.log('addr not exist');
							self._createNumber(m, meas, elementExample);
						}
					});
				});
			});
		});
	},

	_createNumber: function (m, meas, elementExample) {
		console.log('creating number');
		var self = this;    	

		SCWeb.core.Server.resolveScAddr(['number', 'lang_ru', 'lang_en'], function (keynodes) {
			var number = keynodes['number'];
			var lang_ru = keynodes['lang_ru'];
			var lang_en = keynodes['lang_en'];
		
			window.sctpClient.create_node(sc_type_const).done(function (num) {
				console.log('create node num:',num);
				window.sctpClient.create_link().done(function (numName) {
					console.log('create link numName:',numName);
					window.sctpClient.set_link_content(numName, m);
					window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, num, numName).done(function (commonArcFour) {
						window.sctpClient.create_arc(sc_type_arc_pos_const_perm, window.scKeynodes.nrel_system_identifier, commonArcFour);
						window.sctpClient.create_arc(sc_type_arc_pos_const_perm, number, num);
						self._createGramMeasurement(meas, num, elementExample);
					});
				});
				window.sctpClient.create_link().done(function (link_addr) {
					window.sctpClient.set_link_content(link_addr, m);
					window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, num, link_addr).done(function (arc_addr) {
						window.sctpClient.create_arc(sc_type_arc_pos_const_perm, lang_ru, link_addr);
						window.sctpClient.create_arc(sc_type_arc_pos_const_perm, lang_en, link_addr);
						window.sctpClient.create_arc(sc_type_arc_pos_const_perm, window.scKeynodes.nrel_main_idtf, arc_addr);
					});
				});
			});
		});
	},

	_createGramMeasurement: function (meas, numb, elementExample) {
		var self = this;
		console.log('creating grams for numb',numb);
		SCWeb.core.Server.resolveScAddr(['rrel_gram'], function (keynodes) {
		var rrelGram = keynodes['rrel_gram'];
			window.sctpClient.create_arc(sc_type_arc_pos_const_perm, meas, numb).done(function (arcOne) {
				window.sctpClient.create_arc(sc_type_arc_pos_const_perm, rrelGram, arcOne).done(function () {
					self._findChemicalAmount(elementExample);
				});
			});
		});
	}
};