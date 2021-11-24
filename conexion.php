<?php

class conexion{
    const user='root';
    const pass='';
    const db='grupo1';
    const servidor='localhost';

    public function conectarDb(){
        $conectar = new mysqli(self::servidor,self::user,self::pass,self::db);
        if($conectar->connect_errno){
            die("Error en la conección ".$conectar->connect_error);
        }
        return $conectar;
    }
}
//create table clientes(id int primary key auto_increment, dispositivo varchar(10),temperatura float, pulso float,oxigeno float,codigo int);
//UPDATE clientes SET temperatura='$temp', oxigeno='$oxig', pulso='$pulso' where id='$row[0]'"
//create table historico(id int PRIMARY KEY AUTO_INCREMENT, 
//variable varchar(10), 
//clientes_id int not null,
//valor float,
//fecha DateTime, 
//foreign KEY (clientes_id) 
//REFERENCES clientes(id));

//INSERT INTO `clientes`(`id`, `dispositivo`, `temperatura`, `pulso`, `oxigeno`, `codigo`) VALUES (1,'tarjeta1',0,0,0,1)
//UPDATE `clientes` SET`temperatura`=0,`pulso`=0,`oxigeno`=0,`codigo`=1 WHERE 1

//https://162.243.166.76:5080/Grupo1/carga.php?dispositivo=tarjeta1&pulso=32&oxigeno=96&temperatura=35

//DB_USER', 'wordpress'
//DB_PASSWORD', 'bcViMnngI7wz'
//'DB_HOST', 'wordpress-db-ale:3306'
//mysql -h localhost -u root -p
//mysql -h localhost -u wordpress -p
//ssh cucai@wordpress-db-ale


//$host = "wordpress-db-ale:3306";
//$user = "cucai";
//$pass = "voluntad229";
//$db = "agenda2";

?>