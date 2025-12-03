<template>
  <div class="card bg-base-100 shadow-xl hover:shadow-2xl transition-shadow">
    <div class="card-body">
      <h2 class="card-title">{{ title }}</h2>
      <p>{{ description }}</p>
      <div class="card-actions justify-end mt-4">
        <router-link :to="{ name: routeName }" :class="['btn', buttonClass || 'btn-primary']">
          {{ buttonText }}
        </router-link>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
defineProps<{
  title: string;
  description: string;
  routeName: string;
  buttonText: string;
  buttonClass?: string;
}>();
</script>
