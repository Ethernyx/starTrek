<?php
enum OBJETS: int {
    case NONE = -1;
    case PLANETE = 0;
    case SPACESHIP = 1;
    case HEROS = 2;
    case PNJ = 3;
    case EVIL = 4;
    case MISSION = 5;
    case ITEM = 6;
    case GRADE = 7;

    public static function fromName(string $name): string
    {
        foreach (self::cases() as $status) {
            if( $name === $status->name ){
                return $status->value;
            }
        }
        throw new \ValueError("$name is not a valid backing value for enum " . self::class );
    }
}