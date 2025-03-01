<div class="my_popup">
    <div class="my_popup_header">
        <div command>Ajouter un être vivant</div>
    </div>
    <div class="my_popup_content container">
        <h2 class="title rajdhani-bold">Ajouter Un nouvel Habitant dans cet Univers</h2>
        <form id="test" method="post" action="" onsubmit="return false;">
            <input name="request" type="hidden" value="request/search.php" />
            <input name="url" type="hidden" value="addEntities" />
            <div class="row">
                <div class="col-6">
                    <select name="entity_type" class="custom-select sources" data-placeholder="Type d'être vivant">
                        <?php
                        foreach ($types as $id => $type) {
                            echo '<option value="' . $type . '" type>' . $id . '</option>';
                        }
                        ?>
                    </select>
                </div>
            </div>
            <div class="row">
                <div class="col-6">
                    <div class="form-group">
                        <span>Nom</span>
                        <input name="name" class="form-field" type="text" value="">
                    </div>
                </div>
                <div class="col-6">
                    <div class="form-group">
                        <span>AP</span>
                        <input name="ap" class="form-field" type="number" value="">
                    </div>
                </div>
                <div class="col-6">
                    <div class="form-group">
                        <span>HP</span>
                        <input name="hp" class="form-field" type="number" value="">
                    </div>
                </div>
                <div class="col-6">
                    <div class="form-group">
                        <span>DP</span>
                        <input name="dp" class="form-field" type="number" value="">
                    </div>
                </div>
                <div class="col-6">
                    <select name="id_grade" class="custom-select sources" data-placeholder="Grade" data-entity="7"
                        onload="getInfos(this);" data-option-default="Aucun grade">
                    </select>
                </div>
                <div class="col-6">
                    <select name="id_ship" class="custom-select sources" data-placeholder="Vaisseau" data-entity="1"
                        onload="getInfos(this);" data-option-default="Aucun vaisseau">
                    </select>
                </div>
                <div class="col-6">
                    <select name="id_planet" class="custom-select sources" data-placeholder="Planète" data-entity="0"
                        onload="getInfos(this);" data-option-default="Aucune planete">
                    </select>
                </div>
                <div class="col-6">
                    <select name="id_planet_origin" class="custom-select sources" data-placeholder="Planète d'origine"
                        data-entity="0" onload="getInfos(this);" data-option-default="Aucune planete d'origine">
                    </select>
                </div>
            </div>
            <button type="submit" onclick="submitForm(this);">Envoyer</button>
        </form>
    </div>
</div>