// import apiClient from './axios';

export default {
  async calculateLCM(a: number, b: number): Promise<number> {
    // TODO: Replace with actual API call when backend is ready
    // const response = await apiClient.post('/math/lcm', { a, b });
    // return response.data.result;

    // Mock implementation
    return new Promise((resolve) => {
      setTimeout(() => {
        const gcd = (x: number, y: number): number => (!y ? x : gcd(y, x % y));
        const lcm = (x: number, y: number): number => (x * y) / gcd(x, y);
        resolve(lcm(a, b));
      }, 500);
    });
  },

  async calculateGCD(a: number, b: number): Promise<number> {
    // TODO: Replace with actual API call when backend is ready
    // const response = await apiClient.post('/math/gcd', { a, b });
    // return response.data.result;

    // Mock implementation
    return new Promise((resolve) => {
      setTimeout(() => {
        const gcd = (x: number, y: number): number => (!y ? x : gcd(y, x % y));
        resolve(gcd(a, b));
      }, 500);
    });
  }
};
