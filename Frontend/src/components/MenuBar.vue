<template>
<div class="navbar bg-base-300 shadow-sm relative z-50">
  <router-link :to ="{ name: 'home'}" class="btn btn-ghost text-xl">Home</router-link> 


  <div class="relative group flex items-center">
    <button class="btn btn-ghost text-xl" popovertarget="popover-1" style="anchor-name:--anchor-1">
      Utilities
    </button>
    
    <!-- Connecting Line & Selected Utility Name -->
    <div v-if="isUtilityActive" class="hidden lg:flex items-center absolute left-full top-1/2 -translate-y-1/2 ml-2 whitespace-nowrap">
      <div class="w-8 h-0.5 bg-base-content opacity-50 mr-2"></div>
      <span class="text-xl">{{ activeUtilityName }}</span>
    </div>
  </div>

<ul class="dropdown menu w-52 rounded-box bg-base-100 shadow-sm"
  popover id="popover-1" style="position-anchor:--anchor-1">
  <li><router-link :to="{ name: 'lcm' }" active-class="active">Least Common Multiple</router-link></li>
  <li><router-link :to="{ name: 'gcd' }" active-class="active">Greatest Common Denominator</router-link></li>
</ul>


</div>
</template>



<script setup lang="ts">
import { computed } from 'vue';
import { useRoute } from 'vue-router';

const route = useRoute();

const isUtilityActive = computed(() => {
  return ['lcm', 'gcd'].includes(route.name as string);
});

const activeUtilityName = computed(() => {
  if (route.name === 'lcm') return 'Least Common Multiple';
  if (route.name === 'gcd') return 'Greatest Common Denominator';
  return '';
});
</script>