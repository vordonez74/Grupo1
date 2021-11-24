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
//create table clientes(id int primary key auto_increment, dispositivo varchar(10),temp float, pulso float,oxigeno float,codigo int);
//create table historico(id int PRIMARY KEY AUTO_INCREMENT, 
//variable varchar(10), 
//clientes_id int not null,
//valor float,
//fecha DateTime, 
//foreign KEY (clientes_id) 
//REFERENCES clientes(id));

//http://192.168.0.20/grupo1/carga.php?dispositivo=tarjeta1&pulso=32&oxigeno=96&temperatura=35

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