<?php
include_once "define.php";

$json = array("security" => "je préfère le Faucon Millenium", "command" => $_POST["url"], "startrek" => array());


if (strcmp($_POST["url"], "addEntities") == 0) {
    $params = [];
    switch ($_POST["entity_type"]) {
        case OBJETS::PLANETE:
            $params = array(
                "entity_type" => intval($_POST["entity_type"]),
                "name" => $_POST["name"],
                "description" => $_POST["description"],
            );
            break;
        case OBJETS::SPACESHIP:
            $params = array(
                "entity_type" => intval($_POST["entity_type"]),
                "name" => $_POST["name"],
                "ap" => intval($_POST["ap"]),
                "dp" => intval($_POST["dp"]),
                "hp" => intval($_POST["hp"]),
                "description" => $_POST["description"]
            );
            break;
        case OBJETS::GRADE:
            $params = array(
                "entity_type" => intval($_POST["entity_type"]),
                "name" => $_POST["name"],
                "level" => intval($_POST["level"])
            );
            break;
        case OBJETS::fromName("EVIL"):
        case OBJETS::fromName("HEROS"):
        case OBJETS::fromName("PNJ"):
            $params = array(
                "entity_type" => intval($_POST["entity_type"]),
                "name" => $_POST["name"],
                "ap" => intval($_POST["ap"]),
                "dp" => intval($_POST["dp"]),
                "hp" => intval($_POST["hp"]),
                "id_planet" => intval($_POST["id_planet"]),
                "id_ship" => intval($_POST["id_ship"]),
                "id_planet_origin" => intval($_POST["id_planet_origin"]),
                "id_grade" => intval($_POST["id_grade"])
            );
            break;
        case OBJETS::ITEM:
            $params = array(
                "entity_type" => intval($_POST["entity_type"]),
                "name" => $_POST["name"],
                "stat" => intval($_POST["stat"]),
                "effect" => intval($_POST["effect"]),
                "id_owner" => intval($_POST["id_owner"]),
                "type_owner" => intval($_POST["type_owner"]),
            );
            break;
        default:
            echo "ERROR\n";
            break;
    }
    $json['startrek'][] = new ArrayObject($params);
}

$fp = stream_socket_client("tcp://172.22.116.231:8888", $errno, $errstr);
if (!$fp) echo "ERREUR : $errno - $errstr<br />\n";
else {
    $contents = "";
    fwrite($fp, json_encode($json, JSON_UNESCAPED_UNICODE));
    while (!json_decode($contents)) {
        $contents .= fread($fp, 1024);
    }
    echo $contents;
}



