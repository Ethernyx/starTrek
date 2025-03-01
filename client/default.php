<?php 
include_once "function.php";
include_once "header.php";

$infos = new Infos;
$types = array("Heros" => OBJETS::fromName("HEROS"), "Pnjs" => OBJETS::fromName("PNJ"), "Evils" => OBJETS::fromName("EVIL"));

?>

<div class="container">
    <div class="row">
        <div class="col">
            <div class="carte planetes">
                <div class="titre">Liste des planètes disponible :</div>
                <ul>
                    <?php
                        foreach ($infos->__get("planetes") as $planete) {
                            echo '<li data-id="' . $planete->id . '"' . '>' . $planete->name . '<ul>';
                            foreach ($infos->__get("vivants") as $id => $humains) {
                                foreach ($humains as $humain) {
                                    if ($planete->id == $humain->id_planet) {
                                        echo '<li data-id="' . $humain->id . '"' . ' class="' . strtolower($id) . '">' . $humain->name;
                                        if ($infos->hasItems($humain->id, $types[$id])) {
                                            echo '<ul>';
                                            foreach ($infos->__get("objets") as $obj) {
                                                if ($obj->id_owner == $humain->id) echo '<li data-id="' . $obj->id . '">' . $obj->name . '</li>';
                                            }
                                            echo '</ul>';
                                        }
                                        echo '</li>';
                                    }
                                }
                            }
                            echo '</ul></li>';
                        }
                    ?>
                </ul>
            </div>
        </div>
        <div class="col">
            <div class="carte vaisseaux">
                <div class="titre">Liste des vaisseaux disponible :</div>
                <ul>
                    <?php
                        foreach ($infos->__get("vaisseaux") as $vaisseau) {
                            echo '<li data-id="' . $vaisseau->id . '"' . '>' . $vaisseau->name . '<ul>';
                            foreach ($infos->__get("vivants") as $id => $humains) {
                                foreach ($humains as $humain) {
                                    if ($vaisseau->id == $humain->id_ship) {
                                        echo '<li data-id="' . $humain->id . '"' . ' class="' . strtolower($id) . '">' . $humain->name;
                                        if ($infos->hasItems($humain->id, $types[$id])) {
                                            echo '<ul>';
                                            foreach ($infos->__get("objets") as $obj) {
                                                if ($obj->id_owner == $humain->id) echo '<li data-id="' . $obj->id . '">' . $obj->name . '</li>';
                                            }
                                            echo '</ul>';
                                        }
                                        echo '</li>';
                                    }
                                    
                                }
                            }
                            echo '</ul></li>';
                        }
                    ?>
                </ul>
            </div>
        </div>
        <div class="col">
            <div class="carte grades">
                <div class="titre">Liste des grades disponible :</div>
                <ul>
                    <?php
                        foreach ($infos->__get("grades") as $grade) {
                            echo '<li data-id="' . $grade->id . '"' . '>' . $grade->name . ' => level: ' . $grade->level . '</li>';
                        }
                    ?>
                </ul>
            </div>
        </div>
        <div class="col">
            <div class="carte missions">
                <div class="titre">Liste des grades disponible :</div>
                <ul>
                    <?php
                        foreach ($infos->__get("missions") as $mission) {
                            echo '<li data-id="' . $mission->id . '"' . 'class="' . ($mission->is_complete ? "green" : "blue") . '">' . $mission->name . '</li>';
                        }
                    ?>
                </ul>
            </div>
        </div>
        <div class="col">
            <div class="carte missions">
                <div class="titre">Liste des objets sans propriétaire :</div>
                <ul>
                    <?php
                        foreach ($infos->__get("objets") as $obj) {
                            if ($obj->id_owner == 0) echo '<li data-id="' . $obj->id . '"' . 'class="' . '">' . $obj->name . '</li>';
                        }
                    ?>
                </ul>
            </div>
        </div>
    </div>
    <div class="row">
        <div class="col">
            <div>Ajouter un nouvel être vivant :</div>
        </div>
    </div>
    <select name="command" id="command" class="custom-select">
        </select>

        <button  id="list_request">Confirmer</button>
    <?php include_once "popups/addLiving.php" ?>
    <?php include_once "popups/addPlanet.php" ?>
    <?php include_once "popups/addShip.php" ?>
    <?php include_once "popups/addGrade.php" ?>
    <?php include_once "popups/addMission.php" ?>
    <?php include_once "popups/addItem.php" ?>
</div>


<?php include_once "footer.php" ?>