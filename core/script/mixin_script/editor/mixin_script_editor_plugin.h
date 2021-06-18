#ifndef MIXIN_SCRIPT_EDITOR_PLUGIN_H
#define MIXIN_SCRIPT_EDITOR_PLUGIN_H

#include "../mixin_script.h"

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"

class EditorInspectorPluginMixinScript : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginMixinScript, EditorInspectorPlugin);
	
	Ref<MixinScript> script;
	
	void _on_edit_pressed();
	
protected:
	static void _bind_methods();

public:
	virtual bool can_handle(Object *p_object);
	virtual void parse_category(Object *p_object, const String &p_parse_category);
};

class MixinScriptEditorPlugin : public EditorPlugin {
	GDCLASS(MixinScriptEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const { return "MixinScript"; }

	MixinScriptEditorPlugin(EditorNode *p_node);
};

#endif // MIXIN_SCRIPT_EDITOR_PLUGIN_H
