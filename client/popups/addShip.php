<div class="my_popup">
    <div class="my_popup_header">
        <div command>Ajouter un vaisseau</div>
    </div>
    <div class="my_popup_content container">
        <h2 class="title rajdhani-bold">Ajouter Un nouveau vaisseau</h2>
        <form id="test" method="post" action="" onsubmit="return false;">
            <input name="request" type="hidden" value="request/search.php" />
            <input name="url" type="hidden" value="addEntities" />
            <input name="entity_type" type="hidden" value="<?php echo OBJETS::fromName("SPACESHIP") ?>" />
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
                    <div class="form-group">
                        <textarea name="description" class="form-field" placeholder="Description"></textarea>
                    </div>
                </div>
            </div>
            <button type="submit" onclick="submitForm(this);">Envoyer</button>
        </form>
    </div>
</div>