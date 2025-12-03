import apiClient from './axios';

export default {

  async GCD(a: string, b: string) {
    try {
      const response = await apiClient.get(`/gcd/${a}/${b}`);
      console.log('GCD response:', response);
      return response.data.result;
    } catch (error) {
      console.error('error fetching GCD:', error);
      throw error;
    }
  },

  async LCM(a: string, b: string) {
    try {
      const response = await apiClient.get(`/lcm/${a}/${b}`);
      console.log('LCM response:', response);
      return response.data.result;
    } catch (error) {
      console.error('error fetching LCM:', error);
      throw error;
    }
  },

};
