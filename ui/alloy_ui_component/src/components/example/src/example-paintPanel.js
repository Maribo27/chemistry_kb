/**
 * Paint panel.
 */

Example.PaintPanel = function (containerId) {
    this.containerId = containerId;
};

Example.PaintPanel.prototype = {

    init: function () {
        this._initMarkup(this.containerId);
    },

    _initMarkup: function (containerId) {
        var container = $('#' + containerId);

        var self = this;
        container.append('<div class="sc-no-default-cmd">Сплавы</div></div>');
        container.append('<button id="newButton" type="button">Найти компоненты заданного сплава</button>');
        container.append('<button id="searchInfoButton" type="button">Посмотреть раздел Сплавы</button>');
        //If you don't want to make default command - add class="sc-no-default-cmd" to button

        $('#newButton').click(function () {
			self._showMainMenuNode();
		});


		$('#searchInfoButton').click(function () {
			self._findMainIdentifier();
		});

		$('#generateNodes').click(function () {
			self._generateNodes();
		});
    },

    /* Call agent of searching semantic neighborhood,
	send ui_main_menu node as parameter and add it in web window history
	*/
	_showMainMenuNode: function () {
		var addr;
		// Resolve sc-addr. Get sc-addr of ui_main_menu node
		SCWeb.core.Server.resolveScAddr([SCWeb.core.Arguments._arguments[0]], function (keynodes) {
			console.log("key", keynodes);
			console.log("arguments", SCWeb.core.Arguments._arguments[0]);
			addr = SCWeb.core.Arguments._arguments[0];
			// Resolve sc-addr of ui_menu_view_full_semantic_neighborhood node
			SCWeb.core.Server.resolveScAddr(["ui_menu_find_alloy_components"],
			function (data) {
				// Get command of ui_menu_view_full_semantic_neighborhood
				var cmd = data["ui_menu_find_alloy_components"];
				// Simulate click on ui_menu_view_full_semantic_neighborhood button
				SCWeb.core.Main.doCommand(cmd,
				[addr], function (result) {
					// waiting for result
					if (result.question != undefined) {
						// append in history
						SCWeb.ui.WindowManager.appendHistoryItem(result.question);
					}
				});
			});
		});
	},

	_findMainIdentifier: function () {
		var addr;
		// Resolve sc-addr. Get sc-addr of ui_main_menu node
		SCWeb.core.Server.resolveScAddr(['section_subject_domain_of_alloys'], function (keynodes) {
			addr = keynodes['section_subject_domain_of_alloys'];
			// Resolve sc-addr of ui_menu_view_full_semantic_neighborhood node
			SCWeb.core.Server.resolveScAddr(["ui_menu_view_full_semantic_neighborhood"],
			function (data) {
				// Get command of ui_menu_view_full_semantic_neighborhood
				var cmd = data["ui_menu_view_full_semantic_neighborhood"];
				// Simulate click on ui_menu_view_full_semantic_neighborhood button
				SCWeb.core.Main.doCommand(cmd,
				[addr], function (result) {
					// waiting for result
					if (result.question != undefined) {
						// append in history
						SCWeb.ui.WindowManager.appendHistoryItem(result.question);
					}
				});
			});
		});
    }
};