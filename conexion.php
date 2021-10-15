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

?>