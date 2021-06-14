extends "res://addons/gut/test.gd"

class ScriptA extends MultiScriptOwner:
	# warning-ignore:unused_class_variable
	var foo_a = "Foo A"
	func bar_a():
		return "Bar A"

class ScriptB extends MultiScriptOwner:
	# warning-ignore:unused_class_variable
	var foo_b = "Foo B"
	func bar_b():
		return "Bar B"
	func test_get_owner():
		return owner


func test_two_scripts():
	var ms = MultiScript.new()
	ms.script_a = ScriptA
	ms.script_b = ScriptB

	var n = Node.new() # Object *p_this
	n.set_script(ms)
	add_child_autofree(n)

	assert_true(n.test_get_owner() == n)

	assert_eq(n.foo_a, "Foo A")
	assert_eq(n.bar_a(), "Bar A")
	assert_eq(n.foo_b, "Foo B")
	assert_eq(n.bar_b(), "Bar B")


func test_two_scripts__missing_b():
    pending("Should not crash, at least in debug") # FIXME
    # warning-ignore:unreachable_code
    return

    var ms = MultiScript.new()
    ms.script_a = ScriptA
    # ms.script_b = ScriptB  # Oops!

    var n = Node.new()
    n.set_script(ms)
    add_child_autofree(n)

    assert_eq(n.foo_b, "Foo B", "Should not crash")
    assert_eq(n.bar_b(), "Bar B", "Should not crash")
