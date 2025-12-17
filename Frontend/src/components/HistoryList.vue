<template>
  <div v-if="history.length > 0" class="card w-full max-w-lg bg-base-100 shadow-xl">
    <div class="card-body">
      <h3 class="card-title text-lg mb-4">Recent History</h3>
      
      <div class="overflow-x-auto">
        <table class="table table-zebra w-full text-sm">
          <thead>
            <tr>
              <th>Time</th>
              <th>Inputs</th>
              <th>Result</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(item, index) in history" :key="index">
              <td class="text-xs text-base-content/70">
                {{ formatTime(item.timestamp) }}
              </td>
              <td>{{ item.a }}, {{ item.b }}</td>
              <td class="font-bold text-primary">{{ item.result }}</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import type { HistoryItem } from '../composables/useHistory';

defineProps<{
  history: HistoryItem[];
}>();

const formatTime = (timestamp: number) => {
  return new Date(timestamp).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit' });
};
</script>
