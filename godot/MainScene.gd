extends Node2D

onready var GodotGameIA = preload("res://package/bin/godot-game-ia.gdns").new()
onready var chat_id = 118716073

func _on_Dialog_popup_show():
	GodotGameIA.register_callback(self, chat_id)


func _on_Dialog_text_sent(msg)->void:
	#yield(get_tree().create_timer(1), "timeout")
	#$Dialog.add_text("Respuesta automática a " + msg)
	GodotGameIA.send_message(msg, chat_id)

func gdscript_callback(msg):
	#print("Called back from native C++ code: " + msg)
	$Dialog.add_text("Johnny: " + msg)


func _on_Dialog_popup_hide():
	var motion = Vector2(-12800, 0)
	$MainCharacter.move_and_slide(motion)

