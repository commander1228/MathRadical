<script setup lang="ts">
import { onMounted } from 'vue';
import MenuBar from './components/MenuBar.vue';
import { RouterView } from 'vue-router'


onMounted(() => {
  // Sets the theme to 'light' when the app loads
  document.documentElement.setAttribute('data-theme', 'synthwave');
});
</script>

<template>
  <div class="min-h-screen">
    <MenuBar />
    <RouterView />
  </div>
</template>