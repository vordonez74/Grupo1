<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-KyZXEAg3QhqLMpG8r+8fhAXLRk2vvoC2f3B09zVXn8CA5QIVfZOJ3BCsw2P0p/We" crossorigin="anonymous">    
</head>
<body>
    <div class="container">
      <!--
      <div class="row">
          <form action="carga.php" method="GET">
              <div class="mb-3">
                  <input type="text" id="Dispositivo" class="form-control" placeholder="Dispositivo" name="dispositivo">
                </div>
                <div class="mb-3">
                  <input type="text" id="Oxigeno" class="form-control" placeholder="Oxigeno" name="oxigeno">
                </div>
                <div class="mb-3">
                  <input type="text" id="Pulso" class="form-control" placeholder="Pulso" name="pulso">
                </div>      
                <div class="mb-3">
                  <input type="text" id="Temperatura" class="form-control" placeholder="Temperatura" name="temperatura">
                </div>                                    
              <button type="submit" class="btn btn-primary">Alta</button>
            </form>
      </div>
      -->
      <div class="row">
          <?php
            require_once('conexion.php');
            $conexion = new conexion();
            $solicitud = "Select * from historico";
            $resultado = mysqli_query($conexion->conectarDb(), $solicitud);
            echo "<table class='table'><tr><th>Dispositivo</th><th>Variable</th><th>Valor</th><th>Fecha</th><th>Accion</th></tr>";
            while($fila =mysqli_fetch_array($resultado)){
                echo "<tr>";
                echo "<td>".$fila['id']."</td>";
                echo "<td>".$fila['variable']."</td>";
                echo "<td>".$fila['valor']."</td>";
                echo "<td>".$fila['fecha']."</td>";
                echo "<td><a href='baja.php?id=".$fila['id']."'>Eliminar</a></td>";
                echo "</tr>";
            }
            echo "</table>";
          ?>          
        </div>
      </div>      
    </div>
    
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.3/dist/umd/popper.min.js" integrity="sha384-eMNCOe7tC1doHpGoWe/6oMVemdAVTMs2xqW4mwXrXsW0L84Iytr2wi5v2QjrP/xp" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.min.js" integrity="sha384-cn7l7gDp0eyniUwwAZgrzD06kc/tftFf19TOAs2zVinnD/C7E91j9yyk5//jjpt/" crossorigin="anonymous"></script>   
</body>
</html>