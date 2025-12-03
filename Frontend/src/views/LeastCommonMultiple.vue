<template>
  <TwoInputResult 
    title="Least Common Multiple"
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
const result = ref<string | null>(null);

const handleCalculate = async (a: string, b: string) => {
  loading.value = true;
  result.value = null;
  try {
    result.value = await mathService.LCM(a, b);
  } catch (error) {
    console.error('Error calculating LCM:', error);
    // Handle error (e.g., show toast)
  } finally {
    loading.value = false;
  }
};
</script>