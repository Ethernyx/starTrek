<?php
$json = array("security" => "je préfère le Faucon Millenium", "command" => $_GET["command"]);
$params = [];
if (strcmp($_GET["command"], "getInfos") == 0) {
    $params["entity_type"] = intval($_GET["entity_type"]);
}
$json['startrek'] = new ArrayObject($params);


$fp = stream_socket_client("tcp://172.22.116.231:8888", $errno, $errstr);
if (!$fp) echo "ERREUR : $errno - $errstr<br />\n";
else {
    $contents = "";
    fwrite($fp, json_encode($json, JSON_UNESCAPED_UNICODE));
    while (!json_decode($contents)) {
        $contents .= fread($fp, 2048);
    }
    echo $contents;
}
