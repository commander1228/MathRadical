<template>
<div class="navbar bg-base-300 shadow-md relative z-50 px-4 text-white">
  <!-- Brand -->
  <div class="flex-none mr-4">
    <router-link :to ="{ name: 'home'}" class="btn btn-ghost text-xl font-bold tracking-wide text-white">MathRadical</router-link>
  </div>

  <!-- Main Navigation -->
  <div class="flex-1 flex items-center gap-2">
    
    <!-- Permanent Home Link -->
    <router-link :to="{ name: 'home' }" class="btn btn-sm btn-ghost text-white h-9 min-h-[2.25rem] inline-flex items-center justify-center" active-class="btn-active">Home</router-link>

    <!-- Visual Divider -->
    <div class="h-6 w-px bg-white/20 mx-2 self-center"></div>

    <!-- Tools Dropdown (Root of Breadcrumb) -->
    <div class="dropdown dropdown-bottom">
      <div tabindex="0" role="button" class="btn btn-sm btn-ghost font-normal capitalize m-0 text-white h-9 min-h-[2.25rem] inline-flex items-center justify-center">Tools</div>
      <!-- Dropdown Content -->
      <ul tabindex="0" class="dropdown-content z-[100] menu p-2 shadow bg-base-200 rounded-box w-64 mt-2 border border-white/10 text-base-content">
        <li><router-link :to="{ name: 'gcd' }" class="py-2">GCD Validator</router-link></li>
        <li><router-link :to="{ name: 'lcm' }" class="py-2">LCM Calculator</router-link></li>
      </ul>
    </div>

    <!-- Breadcrumb: Active Tool Connection -->
    <!-- Only visible if a tool is active -->
    <div v-if="isToolActive" class="flex items-center gap-2 animate-fade-in ml-1">
        <!-- Chevron Icon -->
        <svg xmlns="http://www.w3.org/2000/svg" class="h-4 w-4 opacity-70 text-white" fill="none" viewBox="0 0 24 24" stroke="currentColor">
          <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5l7 7-7 7" />
        </svg>
        <span class="font-semibold text-white ml-1">{{ currentToolName }}</span>
    </div>

  </div>
</div>
</template>

<script setup lang="ts">
import { computed } from 'vue';
import { useRoute } from 'vue-router';

const route = useRoute();

const isToolActive = computed(() => {
  return ['lcm', 'gcd'].includes(route.name as string);
});

const currentToolName = computed(() => {
  if (route.name === 'lcm') return 'Least Common Multiple';
  if (route.name === 'gcd') return 'Greatest Common Denominator';
  return '';
});
</script>

<style scoped>
.animate-fade-in {
  animation: fadeIn 0.3s ease-in-out;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateX(-5px); }
  to { opacity: 1; transform: translateX(0); }
}
</style>