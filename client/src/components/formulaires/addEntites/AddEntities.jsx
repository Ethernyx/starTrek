import axios from "axios"
import ENTITIES from "../../utils/Entities.tsx"
import "./form-group.scss"
import { Col, Container, InputGroup, Row } from "react-bootstrap"
import Form from 'react-bootstrap/Form';
import { useEffect, useState } from "react";
import useFetch from "../../utils/uses/UseFetch.tsx";
import { useMemo } from "react";

export default function AddEntities({entity_type}) {

    const headerForm = <>
        <input name="request" type="hidden" value="request/search.php" />
        <input name="url" type="hidden" value="addEntities" />
        <input name="entity_type" type="hidden" value={entity_type} />
    </>
    const footerForm = <>
        <button type="submit"></button>
    </>

    const [planete, setPlanete] = useState(null);
    const entity = [{ id: ENTITIES.EVIL, name: "Evil" }, { id: ENTITIES.HEROS, name: "Hero" }, { id: ENTITIES.PNJ, name: "Pnj" }];

    var token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJhZG1pbiIsInN1YiI6InJvbWFpbiIsImlhdCI6MTc0NzQwMDkzNH0.VTymkQMIrkJjjk_ClRK-bscKlqk7jb31Hy7uMyD6Jyw";

    switch (entity_type) {
        case ENTITIES.GRADE:
            return (
                <form>
                    <h2 className="title rajdhani-bold">Ajouter Un nouveau grade</h2>
                    {headerForm}
                    <Container>
                        <Row>
                            <Col>
                                <InputGroup>
                                    <InputGroup.Text >Nom</InputGroup.Text>
                                    <Form.Control placeholder="Tintin" name="name" type="text" />
                                </InputGroup>
                            </Col>
                            <Col>
                                <InputGroup>
                                    <InputGroup.Text >Level</InputGroup.Text>
                                    <Form.Control placeholder="1" name="level" type="number" />
                                </InputGroup>
                            </Col>
                        </Row>
                    </Container>
                    {footerForm}
                </form>
            )
            break;
        case ENTITIES.EVIL:
        case ENTITIES.HEROS:
        case ENTITIES.PNJ:
            const {data, errors} = useFetch("http://127.0.0.1:8888/get_infos", 
                {
                    method: "POST", 
                    body : JSON.stringify({ security: "je préfère le Faucon Millenium", user: "romain", command: "get_infos", startrek : { entity_type : entity_type, }}),
                    headers: {
                        'Authorization': "Bearer " + token + ""
                    }
                });  
            if (data) console.log(data);
            else console.log(errors)
            
            return (
                <form>
                    <h2 className="title rajdhani-bold">Ajouter Un nouveau { entity_type == ENTITIES.EVIL ? "Evil" : (entity_type == ENTITIES.HEROS ? "Hero" : "Pnj") }</h2>
                    {headerForm}
                    <Row>
                        <Col></Col>
                    </Row>
                </form>
            )
            break;
        default:
            break;
    }

    function fillForm() {
        axios.get()
    }

    function submit() {

    }

    return (
        <form>

        </form>
    )
}