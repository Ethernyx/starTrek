const Entities = {
    NONE: -1,
    PLANETE: 0,
    SPACESHIP: 1,
    HEROS: 2,
    PNJ: 3,
    EVIL: 4,
    MISSION: 5,
    ITEM: 6,
    GRADE: 7,
    LIVING: 8
}

const CodeError = {
    NAME: "Le champ Nom doit être renseigné",
    AP: "Le champ AP doit être renseigné et être positif",
    HP: "Le champ HP doit être renseigné et être positif",
    DP: "Le champ DP doit être renseigné et être positif",
    PLANET: "Le champ Planète doit être renseigné",
    PLANET_ORIGIN: "Le champ Planète d'origine doit être renseigné",
    PLANET_OR_SHIP: "Le nouvel habitant doit être OBLIGATOIREMENT sur un vaisseau OU une planète",
    SHIP: "Le champ Vaisseau doit être renseigné",
    DESC: "Le champ Description doit être renseigné",
    LEVEL: "Le champ Level doit être renseigné et être positif",
    ENTITY_TYPE_UNKNOWN: "Le type d'entité est inconnue",
    COMMAND_UNKNOWN: "Commande inconnue",
    STAT: "Le champ stat doit être renseigné",
    EFFECT: "Le champ effet doit être renseigné",
}