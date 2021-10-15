<?php

require_once('conexion.php');

#Recibe los datos
$disp = $_POST['dispositivo'];
$oxig = $_POST['oxigeno'];
$pulso = $_POST['pulso'];
$temp = $_POST['temperatura'];

$conn = new conexion();

$query = "SELECT * FROM dispositivos WHERE idDisp = '$disp'";

$select = mysqli_query($conn->conectarDb(), $query);

if($select->num_rows){ #Verifica si existe el dispositivo
    $query = "UPDATE dispositivos SET oxigeno='$oxig' pulso='$pulso' temperatura = '$temp' WHERE idDisp = '$disp'";
    $update = mysqli_query($conn->conectarDB(),$query);

    $query = "INSERT INTO historial(idDisp, variable, valor, Fecha) VALUES('$disp','oxigeno','$oxig',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);
    $query = "INSERT INTO historial(idDisp, variable, valor, Fecha) VALUES('$disp','pulso','$pulso',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);
    $query = "INSERT INTO historial(idDisp, variable, valor, Fecha) VALUES('$disp','temperatura','$temp',CURRENT_TIMESTAMP)";
    $insert = mysqli_query($conn->conectarDB(),$query);

    $query = "SELECT led FROM dispositivos WHERE idDisp = '$disp'";
    $resultado = mysqli_query($conn->conectarDb(),$query);
    $row = mysqli_fetch_row($resultado);
    echo "{LED:".$row[0]."}";

}else{
    echo "LA TARJETA NO EXISTE <br>";
}

$conn = new conexion();
?>