<template>
  <div class="flex min-h-screen items-center justify-center bg-base-200 p-4">
    <div class="card w-full max-w-lg bg-base-100 shadow-xl">
      <div class="card-body">
        <h2 class="card-title justify-center text-2xl mb-4">{{ title }}</h2>
        
        <div class="flex flex-col gap-4">
          <div class="form-control w-full">
            <label class="label">
              <span class="label-text">{{ label1 }}</span>
            </label>
            <input 
              type="number" 
              v-model="value1" 
              placeholder="Enter first number" 
              class="input input-bordered input-primary w-full" 
            />
          </div>

          <div class="divider"></div>

          <div class="form-control w-full">
            <label class="label">
              <span class="label-text">{{ label2 }}</span>
            </label>
            <input 
              type="number" 
              v-model="value2" 
              placeholder="Enter second number" 
              class="input input-bordered input-secondary w-full" 
            />
          </div>

          <div class="card-actions justify-center mt-6">
            <button 
              class="btn btn-primary w-full" 
              @click="onCalculate" 
              :disabled="loading || !isValidInput"
            >
              <span v-if="loading" class="loading loading-spinner"></span>
              Calculate
            </button>
          </div>

          <div v-if="result !== null" class="alert alert-success mt-4">
            <svg xmlns="http://www.w3.org/2000/svg" class="stroke-current shrink-0 h-6 w-6" fill="none" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
            <span>Result: <span class="font-bold text-lg">{{ result }}</span></span>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';

defineProps<{
  title: string;
  label1: string;
  label2: string;
  loading?: boolean;
  result?: string | null;
}>();

const emit = defineEmits<{
  (e: 'calculate', v1: string, v2: string): void;
}>();

const value1 = ref<string | null>(null);
const value2 = ref<string | null>(null);

const isValidInput = computed(() => {
  
  return (
    value1.value !== null &&
    value2.value !== null &&
    value1.value !== '' &&
    value2.value !== '' &&
    !Number.isNaN(Number(value1.value)) &&
    !Number.isNaN(Number(value2.value))
  );
});

const onCalculate = () => {
  if (isValidInput.value && value1.value !== null && value2.value !== null) {
    emit('calculate', value1.value, value2.value);
  }
};
</script>