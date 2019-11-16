extends Node2D


#TODO: Javi, pon aquí la llamada a la DLL en vez del código del timer
#      Para mostrar algo, usa $Dialog.add_text("...")
func _on_Dialog_text_sent(msg)->void:
	yield(get_tree().create_timer(1), "timeout")
	$Dialog.add_text("Respuesta automática a " + msg)


func _on_Dialog_popup_hide():
	var motion = Vector2(-12800, 0)
	$MainCharacter.move_and_slide(motion)
