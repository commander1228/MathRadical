import axios from 'axios';


// Create an Axios instance with default configuration
const apiClient = axios.create({
    baseURL: import.meta.env.VITE_API_URL,
    headers: {
        'Content-Type': 'application/json',
    },
});


apiClient.interceptors.request.use(
    (config) => {
       
        return config;
    },
    (error) => {
        return Promise.reject(error);
    }
);

export default apiClient;
