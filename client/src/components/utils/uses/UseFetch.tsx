import { useEffect, useState } from "react";


/**
 * 
 * @param {string} url 
 * @param {RequestInit} options 
 */
export default function useFetch(url: string, options: RequestInit = {}, token: string) {
    const [data, setData] = useState(null);
    const [errors, setErrors] = useState(null);

    useEffect(() => {
        fetch(url, {
            ...options,
            headers: {
                'Accept': 'application/json; charset=UTF-8',
                'Content-Type': 'application/json',
                ...options.headers
            }
        }).then(r => {
            if (!r.ok) {
                throw new Error('Network response was not ok');
            } 
            return r.json();
        }).then(data => {
            setData(data)
        }).catch((e) => {
            setErrors(e)
        })
    }, []);

    return {
        data, errors
    }
}