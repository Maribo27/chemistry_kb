/* --- src/pencil-common.js --- */
var PencilComponent = {};

function extend(child, parent) {
    var F = function () {
    };
    F.prototype = parent.prototype;
    child.prototype = new F();
    child.prototype.constructor = child;
    child.superclass = parent.prototype;
}


/* --- src/pencil-paintPanel.js --- */
/**
 * Paint panel.
 */

PencilComponent.PaintPanel = function (containerId) {
    this.containerId = containerId;
};

PencilComponent.PaintPanel.prototype = {

    init: function () {
        this._initMarkup(this.containerId);
    },

    _initMarkup: function (containerId) {
        var container = $('#' + containerId);

        var self = this;
        container.append('<div class="sc-no-default-cmd">Состав</div>');
        self._createButtons(container);

    },

    _createButtons: function (container) {
		var self = this;
        console.log("create buttons");
			var object_node, nrel_main_idtf_addr, nrel_sys_idtf_addr, system_id;
		SCWeb.core.Server.resolveScAddr(['nrel_main_idtf'], function (keynodes) {
			nrel_main_idtf_addr = keynodes['nrel_main_idtf'];
		});
		SCWeb.core.Server.resolveScAddr(['nrel_system_identifier'], function (keynodes) {
			nrel_sys_idtf_addr = keynodes['nrel_system_identifier'];
		});
		SCWeb.core.Server.resolveScAddr(['concept_object'], function (keynodes) {
			object_node = keynodes['concept_object'];
			window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_3F_A_A, [
				object_node,
				sc_type_arc_pos_const_perm,
				0]).done(
				
				function(objects){
					var counter = 0;
					while (counter < objects.length) {
						window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
							objects[counter][2],
							sc_type_arc_common | sc_type_const,
							sc_type_link,
							sc_type_arc_pos_const_perm,
							nrel_sys_idtf_addr]).done(
							
							function(identifiers){  
								window.sctpClient.get_link_content(identifiers[0][2],'string').done(
									function(content){
										system_id = content;
										console.log("system in function", system_id);
										console.log("counter", counter);
									});         
							});

						window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
							objects[counter][2],
							sc_type_arc_common | sc_type_const,
							sc_type_link,
							sc_type_arc_pos_const_perm,
							nrel_main_idtf_addr]).done(

							function(identifiers){  
								window.sctpClient.get_link_content(identifiers[0][2],'string').done(
									function(content){
										container.append('<button id="' + system_id + '" type="button">' + content + '</button>');
										$('#' + system_id).click(function () {
											var name = $(this).attr('id');
											self._play(name);
										});
										console.log("system in function", system_id);
										console.log("content in function", content);
										console.log("counter", counter);
								});         
							});
						counter++;
						console.log("counter check", counter);
					}
				});
		});
	},

    _play: function (name) {
    	var addr;
		// Resolve sc-addr. Get sc-addr of ui_main_menu node
		SCWeb.core.Server.resolveScAddr([name], function (keynodes) {
			console.log("key", keynodes);
			console.log("arguments", SCWeb.core.Arguments._arguments[0]);
			addr = keynodes[name];
			// Resolve sc-addr of ui_menu_view_full_semantic_neighborhood node
			SCWeb.core.Server.resolveScAddr(["ui_menu_find_object_structure"],
			function (data) {
				// Get command of ui_menu_view_full_semantic_neighborhood
				var cmd = data["ui_menu_find_object_structure"];
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

/* --- src/pencil-component.js --- */
/**
 * PencilComponent component.
 */
PencilComponent.DrawComponent = {
    ext_lang: 'pencil_component',
    formats: ['format_pencil_json'],
    struct_support: true,
    factory: function (sandbox) {
        return new PencilComponent.DrawWindow(sandbox);
    }
};

PencilComponent.DrawWindow = function (sandbox) {
    this.sandbox = sandbox;
    this.paintPanel = new PencilComponent.PaintPanel(this.sandbox.container);
    this.paintPanel.init();
    this.recieveData = function (data) {
        console.log("in recieve data" + data);
    };

    var scElements = {};

    function drawAllElements() {
        var dfd = new jQuery.Deferred();
       // for (var addr in scElements) {
            jQuery.each(scElements, function(j, val){
                var obj = scElements[j];
                if (!obj || obj.translated) return;
// check if object is an arc
                if (obj.data.type & sc_type_arc_pos_const_perm) {
                    var begin = obj.data.begin;
                    var end = obj.data.end;
                    // logic for component update should go here
                }

        });
        SCWeb.ui.Locker.hide();
        dfd.resolve();
        return dfd.promise();
    }

// resolve keynodes
    var self = this;
    this.needUpdate = false;
    this.requestUpdate = function () {
        var updateVisual = function () {
// check if object is an arc
            var dfd1 = drawAllElements();
            dfd1.done(function (r) {
                return;
            });


/// @todo: Don't update if there are no new elements
            window.clearTimeout(self.structTimeout);
            delete self.structTimeout;
            if (self.needUpdate)
                self.requestUpdate();
            return dfd1.promise();
        };
        self.needUpdate = true;
        if (!self.structTimeout) {
            self.needUpdate = false;
            SCWeb.ui.Locker.show();
            self.structTimeout = window.setTimeout(updateVisual, 1000);
        }
    }
    
    this.eventStructUpdate = function (added, element, arc) {
        window.sctpClient.get_arc(arc).done(function (r) {
            var addr = r[1];
            window.sctpClient.get_element_type(addr).done(function (t) {
                var type = t;
                var obj = new Object();
                obj.data = new Object();
                obj.data.type = type;
                obj.data.addr = addr;
                if (type & sc_type_arc_mask) {
                    window.sctpClient.get_arc(addr).done(function (a) {
                        obj.data.begin = a[0];
                        obj.data.end = a[1];
                        scElements[addr] = obj;
                        self.requestUpdate();
                    });
                }
            });
        });
    };
// delegate event handlers
    this.sandbox.eventDataAppend = $.proxy(this.receiveData, this);
    this.sandbox.eventStructUpdate = $.proxy(this.eventStructUpdate, this);
    this.sandbox.updateContent();
};
SCWeb.core.ComponentManager.appendComponentInitialize(PencilComponent.DrawComponent);

