extends Node2D

onready var GodotGameIA = preload("res://package/bin/godot-game-ia.gdns").new()
onready var chat_id = 118716073

func _ready():
	GodotGameIA.connect("callback_ready", self, "_on_GodotGameIA_callback_ready")
	GodotGameIA.connect("callback_disconnected", self, "_on_GodotGameIA_callback_disconnected")
	
	
func _on_GodotGameIA_callback_ready(chat_id, msg):
	print("callback ready ('" + str(chat_id) + "'): " + msg)

func _on_GodotGameIA_callback_disconnected(chat_id, msg):
	print("callback disconnected ('" + str(chat_id) + "'): " + msg)


func _on_Dialog_text_sent(msg)->void:
	GodotGameIA.send_message(msg, chat_id)

func gdscript_callback(msg):
	$Dialog.add_text("Johnny: " + msg)

func _on_Dialog_popup_show():
	GodotGameIA.register_callback(self, chat_id)

func _on_Dialog_popup_hide():
	GodotGameIA.remove_callback(chat_id)
	var motion = Vector2(-12800, 0)
	$MainCharacter.move_and_slide(motion)

