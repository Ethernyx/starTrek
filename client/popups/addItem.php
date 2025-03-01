<div class="my_popup">
    <div class="my_popup_header">
        <div command>Ajouter une item</div>
    </div>
    <div class="my_popup_content container">
        <h2 class="title rajdhani-bold">Ajouter Un nouvel item</h2>
        <form id="test" method="post" action="" onsubmit="return false;">
            <input name="request" type="hidden" value="request/search.php" />
            <input name="url" type="hidden" value="addEntities" />
            <input name="entity_type" type="hidden" value="<?php echo OBJETS::fromName("ITEM") ?>" />
            <div class="row">
                <div class="col-6">
                    <div class="form-group">
                        <span>Nom</span>
                        <input name="name" class="form-field" type="text" value="">
                    </div>
                </div>
                <div class="col-6">
                    <select name="id_planet_origin" class="custom-select sources" data-placeholder="Propriétaire"
                        data-entity="8" onload="getInfos(this);" data-option-default="Aucun propriétaire">
                    </select>
                </div>
                <div class="col-6">
                    <div class="form-group">
                        <span>Stat</span>
                        <input name="stat" class="form-field" type="number" value="">
                    </div>
                </div>
                <div class="col-6">
                    <div class="form-group">
                        <span>Effet</span>
                        <input name="effect" class="form-field" type="number" value="">
                    </div>
                </div>
            </div>
            <button type="submit" onclick="submitForm(this);">Envoyer</button>
        </form>
    </div>
</div>