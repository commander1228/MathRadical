import apiClient from './axios';

export interface HelloResponse {
    message: string;
}

export default {
    getHello() {
        return apiClient.get<HelloResponse>('/');
    },

    // Example of a POST request
    // postData(data: any) {
    //   return apiClient.post('/data', data);
    // }
};
