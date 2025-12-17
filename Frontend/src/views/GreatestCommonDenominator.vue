<template>
  <div class="min-h-screen bg-base-200 p-4">
    <div class="flex flex-col lg:flex-row gap-8 items-start justify-center max-w-6xl mx-auto">
      
      <!-- Left Side: Calculator -->
      <TwoInputResult 
        title="Greatest Common Denominator"
        label1="Number 1"
        label2="Number 2"
        :loading="loading"
        :result="result"
        @calculate="handleCalculate"
      />

      <!-- Right Side: History -->
      <HistoryList :history="filteredHistory" />
      
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';
import TwoInputResult from '../components/TwoInputResult.vue';
import HistoryList from '../components/HistoryList.vue';
import mathService from '../api/mathService';
import { useHistory } from '../composables/useHistory';

const { history, addToHistory } = useHistory();

const filteredHistory = computed(() => {
  return history.value.filter(item => item.operation === 'GCD');
});

const loading = ref(false);
const result = ref<string | null>(null);

const handleCalculate = async (a: string, b: string) => {
  loading.value = true;
  result.value = null;
  try {
    result.value = await mathService.GCD(a, b);
    if (result.value) {
      addToHistory({
        a,
        b,
        result: result.value,
        operation: 'GCD'
      });
    }
  } catch (error) {
    console.error('Error calculating GCD:', error);
    // Handle error (e.g., show toast)
  } finally {
    loading.value = false;
  }
};
</script>