<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>

<?php
$flavors= [
    'Pork' => 2,
    'Salmon'=>1,
    'Beef'=>0,
    'Veg'=>5,
];

    ?>
    <h1>Information for <?php echo $_GET["dName"]; ?>'s reservation:</h1>
    <h3>food you've ordered:</h3>
    <?php
    foreach ($_GET['flavor'] as $f){
        echo '<b>-'.$f .': </b>';
        if ($flavors[$f]>0){
            echo 'You got it! we have '. $flavors[$f] .' in stock<br>';
        }
        else{
            echo 'Sorry!'. $f .' is out of stock<br>';
        }
    }

    echo '<h2><I> Thank you for ordering from us!</I></h2><br><br><h3>';
        $whoEat=$_GET['inlineFormCustomSelect'];
        if($whoEat=='usr'){
            echo 'Im not here to judge but dont eat dog food...treat yourself with a McDonalds';
        }
        if($whoEat=='dog'){
            echo 'I bet your dog i thrilled';
        }
        if($whoEat=='both'){
            echo "It's not ok for human to eat dog food but i bet its gonna be one hell of a romantic dinner";
        }
        echo '</h3>'
    ?>
</body>
</html>