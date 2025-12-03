<template>
  <TwoInputResult 
    title="Greatest Common Denominator"
    label1="Number 1"
    label2="Number 2"
    :loading="loading"
    :result="result"
    @calculate="handleCalculate"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import TwoInputResult from '../components/TwoInputResult.vue';
import mathService from '../api/mathService';

const loading = ref(false);
const result = ref<number | null>(null);

const handleCalculate = async (v1: number, v2: number) => {
  loading.value = true;
  result.value = null;
  try {
    result.value = await mathService.calculateGCD(v1, v2);
  } catch (error) {
    console.error('Error calculating GCD:', error);
    // Handle error (e.g., show toast)
  } finally {
    loading.value = false;
  }
};
</script>