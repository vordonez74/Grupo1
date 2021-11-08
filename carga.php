<?php

require_once('conexion.php');

#Recibe los datos
$disp = $_GET['dispositivo'];
$oxig = $_GET['oxigeno'];
$pulso = $_GET['pulso'];
$temp = $_GET['temperatura'];

$conn = new conexion();

$query = "SELECT id FROM clientes WHERE dispositivo = '$disp'";

$select = mysqli_query($conn->conectarDb(), $query);

$row = mysqli_fetch_row($select);

if($select->num_rows){ #Verifica si existe el dispositivo
    $query = "UPDATE clientes SET oxigeno='$oxig' pulso='$pulso' temperatura = '$temp' WHERE id = '$row[0]'";
    $update = mysqli_query($conn->conectarDB(),$query);

    $query = "INSERT INTO historico(clientes_id, variable, valor, Fecha) VALUES('$row[0]','oxigeno','$oxig',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);
    $query = "INSERT INTO historico(clientes_id, variable, valor, Fecha) VALUES('$row[0]','pulso','$pulso',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);
    $query = "INSERT INTO historico(clientes_id, variable, valor, Fecha) VALUES('$row[0]','temperatura','$temp',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);

    $query = "SELECT codigo FROM clientes WHERE id = '$row[0]'";
    $resultado = mysqli_query($conn->conectarDb(),$query);
    $row = mysqli_fetch_row($resultado);
    echo "{codigo:".$row[0]."}";

}else{
    echo "LA TARJETA NO EXISTE <br>";
}

$conn = new conexion();
?>