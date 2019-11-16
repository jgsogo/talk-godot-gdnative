extends Area2D

signal text_sent(msg)
signal popup_hide

onready var msg_box := $PopupPanel/Contents/GhostMsg
onready var input := $PopupPanel/Contents/Input

func add_text(new_text:String) -> void:
	msg_box.text += new_text + "\n"

func _on_Dialog_body_entered(body):
	$Ghost.visible = true
	$PopupPanel.popup_centered()
	get_tree().paused = true


func _on_Dialog_body_exited(body):
	$Ghost.visible = false

func _on_SendButton_pressed():
	msg_box.text += "$ " + input.text + "\n"
	emit_signal("text_sent", input.text)
	input.text = ""

func _on_PopupPanel_popup_hide():
	get_tree().paused = false
	emit_signal("popup_hide")
