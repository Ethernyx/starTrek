<?php
include_once 'define.php';
class   Infos {
    private $planetes = array();
    private $vivants = array();
    private $objets = array();
    private $vaisseaux = array();
    private $missions = array();
    private $grades = array();

    private $json = array(
        "security" => "je préfère le Faucon Millenium", 
        "command" => "getInfos", 
        "startrek" => array("entity_type" => 0));

    private function setPlanetes($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::PLANETE;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->planetes[$array[$i]->id] = $array[$i];
            }
        }
    }

    private function setVivants($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::HEROS;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->vivants["Heros"][$array[$i]->id] = $array[$i];
            }
            $this->json["startrek"]["entity_type"] = OBJETS::EVIL;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->vivants["Evils"][$array[$i]->id] = $array[$i];
            }
            $this->json["startrek"]["entity_type"] = OBJETS::PNJ;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->vivants["Pnjs"][$array[$i]->id] = $array[$i];
            }
        }
    }

    private function setObjets($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::ITEM;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->objets[$array[$i]->id] = $array[$i];
            }
        }
    }

    private function setVaisseaux($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::SPACESHIP;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->vaisseaux[$array[$i]->id] = $array[$i];
            }
        }
    }

    private function setMissions($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::MISSION;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->missions[$array[$i]->id] = $array[$i];
            }
        }
    }

    private function setGrades($fp = null) {
        if (!$fp) $fp = $this->initConnection();
        if ($fp) {
            $this->json["startrek"]["entity_type"] = OBJETS::GRADE;
            $array = $this->request($fp);
            for ($i = 0; $i < count($array); $i++) {
                $this->grades[$array[$i]->id] = $array[$i];
            }
        }
    }

    private function refresh() {
        $fp = $this->initConnection();
        $this->setPlanetes($fp);
        $this->setVivants($fp);
        $this->setObjets($fp);
        $this->setVaisseaux($fp);
        $this->setMissions($fp);
        $this->setGrades($fp);
        
    }

    private function initConnection() {
        $fp = stream_socket_client("tcp://172.22.116.231:8888", $errno, $errstr);
        if (!$fp) echo "ERREUR : $errno - $errstr<br />\n";
        return $fp;
    }

    private function request($fp) {
        $contents = "";
        fwrite($fp, json_encode($this->json, JSON_HEX_AMP));
        while (!json_decode($contents)) {
            $contents .= fread($fp, 1024);
        }
        return json_decode($contents)->return->entities;
    }

    public function __construct() {
        $this->refresh();
    }

    public function __get($property) {
        switch ((string)$property) {
            case "planetes" : return $this->planetes;
            case "vivants" : return $this->vivants;
            case "objets" : return $this->objets;
            case "vaisseaux" : return $this->vaisseaux;
            case "missions" : return $this->missions;
            case "grades" : return $this->grades;
            default : throw new Exception('Propriété ou valeur invalide !');
        }
    }

    public function hasHVivants($planete) {
        foreach ($this->vivants as $vivant) {
            if ($vivant->id_planet == $planete) return true;
        }
        return false;
    }

    public function hasEquipage($vaisseau) {
        foreach ($this->vivants as $vivant) {
            if ($vivant->id_ship == $vivant) return true;
        }
        return false;
    }

    public function hasItems($vivant, $type) {
        foreach ($this->objets as $obj) {
            if ($obj->id_owner == $vivant && $obj->type_owner == $type) return true;
        }
        return false;
    }
}