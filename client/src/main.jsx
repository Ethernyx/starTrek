import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.scss'
import 'bootstrap/dist/css/bootstrap.min.css';
import AddEntities from './components/formulaires/addEntites/AddEntities.jsx'
import ENTITIES from './components/utils/Entities.js'

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <AddEntities entity_type={ENTITIES.PNJ}/>
  </StrictMode>
)
