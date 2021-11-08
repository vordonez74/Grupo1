<?php
require_once('conexion.php');
$conexion = new conexion();
$id = $_GET['id'];
$solicitud = "DELETE FROM historico WHERE id=$id";
$resultado = mysqli_query($conexion->conectarDb(), $solicitud);
header('location: index.php');
?>