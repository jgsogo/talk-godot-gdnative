extends Area2D


onready var msg_box := $PopupPanel/Contents/GhostMsg

func _on_Dialog_body_entered(body):
	$Ghost.visible = true
	$PopupPanel.popup_centered()
	msg_box.text = "epepepepepe"


func _on_Dialog_body_exited(body):
	$Ghost.visible = false
	$PopupPanel.hide()
