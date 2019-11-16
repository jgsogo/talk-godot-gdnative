extends Area2D

signal text_sent

onready var msg_box := $PopupPanel/Contents/GhostMsg
onready var input := $PopupPanel/Contents/Input

func add_text(new_text:String) -> void:
	msg_box.text += new_text + "\n"

func _on_Dialog_body_entered(body):
	$Ghost.visible = true
	$PopupPanel.popup_centered()


func _on_Dialog_body_exited(body):
	$Ghost.visible = false
	$PopupPanel.hide()


func _on_SendButton_pressed():
	msg_box.text += "$ " + input.text + "\n"
	input.text = ""
	emit_signal("text_sent")
