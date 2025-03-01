

function submitForm(form) {
    form = $(form).parent();
    if (!checkForm(form)) return;
    $.ajax({
        url: $(form).find("[name='request']").val(),
        type: "POST",
        data: $(form).serialize(),
        success: function (data) {
            console.log(JSON.parse(data));
        },
        error: function () {

        }
    });
}

var popups = new Array();
const my_popups = $(".my_popup").each(function (id) {
    var popup = new Popup({
        id: popups.length,
        title: "toto",
        hideTitle: true,
        borderRadius: "15px",
        closeColor: "#fff",
        disableScroll: false,
        heightMultiplier: 0.33,
        content: $(this).html()
    });
    popups.push(popup);

    $(this).attr("id-popup", id);
    $("#command").append('<option value="' + id + '">' + $(this).find('[command]').html() + '</option>');

}).promise().done(function () {
    custom_select_build($("body"));
});

$("#list_request").click(function () {
    var id = $("#command").val();
    // je vire les p inutile
    var html = $(".popup." + id).html();
    html = html.replace(/<p>/g, "");
    html = html.replace(/<\/p>/g, "");
    html = html.replace(/&nbsp;/g, "");
    $(".popup." + id).html(html);
    if ($(".popup." + id + " .custom-select-wrapper").length != $(".popup." + id + " select").length) {
        custom_select_build($(".popup." + id));
    }
    popups[$("#command").val()].show();
    $(".popup." + id).find("select").each(function () {
        this.dispatchEvent(new Event('load'));
    });
});


function getInfos(select) {
    var data = {
        "entity_type": parseInt($(select).attr("data-entity")),
        "command": "getInfos"
    };
    $.ajax({
        url: "requests/my_get.php",
        type: "GET",
        data: data,
        success: function (data) {
            var json = JSON.parse(data);
            console.log(json);
            $(select).empty();
            if ($(select).attr("data-option-default")) {
                $(select).append('<option value="0">' + $(select).attr("data-option-default") + '</option>');
            }
            json.return.entities.forEach(entity => {
                $(select).append('<option value="' + entity.id + '">' + entity.name + '</option>');
            });
            checkOptions($(select).parent());
            checkEvent("body");
        },
        error: function () {
        }
    });
}

function checkForm(form) {
    var command = $(form).find("[name=url]").val();
    var error = []
    console.log(Entities.NONE);
    switch (command) {
        case "addEntities":
            var entity_type = parseInt($(form).find("[name=entity_type]").val());
            switch (entity_type) {
                case Entities.PLANETE: 
                case Entities.MISSION:
                    if (!$(form).find("[name=name]").val()) error.push(CodeError.NAME);
                    if (!$(form).find("[name=description]").val()) error.push(CodeError.DESC);
                    break;
                case Entities.SPACESHIP: 
                    if (!$(form).find("[name=name]").val()) error.push(CodeError.NAME);
                    if (!$(form).find("[name=ap]").val() || parseInt($(form).find("[name=ap]").val()) <= 0) error.push(CodeError.AP);
                    if (!$(form).find("[name=hp]").val() || parseInt($(form).find("[name=hp]").val()) <= 0) error.push(CodeError.HP);
                    if (!$(form).find("[name=dp]").val() || parseInt($(form).find("[name=dp]").val()) <= 0) error.push(CodeError.DP);
                    if (!$(form).find("[name=description]").val()) error.push(CodeError.DESC);
                    break;
                case Entities.HEROS: 
                case Entities.PNJ:
                case Entities.EVIL:
                    if (!$(form).find("[name=name]").val()) error.push(CodeError.NAME);
                    if (!$(form).find("[name=ap]").val() || parseInt($(form).find("[name=ap]").val()) <= 0) error.push(CodeError.AP);
                    if (!$(form).find("[name=hp]").val() || parseInt($(form).find("[name=hp]").val()) <= 0) error.push(CodeError.HP);
                    if (!$(form).find("[name=dp]").val() || parseInt($(form).find("[name=dp]").val()) <= 0) error.push(CodeError.DP);
                    if ($(form).find("[name=id_planet_origin]").val() == 0) error.push(CodeError.PLANET_ORIGIN);
                    if ($(form).find("[name=id_planet]").val() == 0 && $(form).find("[name=id_ship]").val() == 0) error.push(CodeError.PLANET_OR_SHIP);
                    if ($(form).find("[name=id_planet]").val() != 0 && $(form).find("[name=id_ship]").val() != 0) error.push(CodeError.PLANET_OR_SHIP);
                    break;
                case Entities.ITEM:
                    if (!$(form).find("[name=name]").val()) error.push(CodeError.NAME);
                    if (!$(form).find("[name=stat]").val()) error.push(CodeError.STAT);
                    if (!$(form).find("[name=effect]").val()) error.push(CodeError.EFFECT);
                    break;
                case Entities.GRADE:
                    if (!$(form).find("[name=name]").val()) error.push(CodeError.NAME);
                    if (!$(form).find("[name=level]").val()) error.push(CodeError.LEVEL);
                    break;
                default:
                    error.push(CodeError.ENTITY_TYPE_UNKNOWN);
                    break;
            }
            break;
        default:
            error.push(CodeError.COMMAND_UNKNOWN);
            break;
    }
    if (error.length > 0) return listError(error);
    return true;
}

function listError(error) {
    var msg = "<ul>";
    error.forEach(function(elem) {
        msg += ("<li>" + elem + "</li>");
    })
    msg += "</ul>"
    statusPopup("error", msg);
    return false;
}

function statusPopup(type, msg) {
    swal.fire({
        icon: type == "success" ? "success" : "error",
        title: type == "success" ? "Félicitation!" : "Erreur!",
        html: msg,
        theme: "dark"
    });
}