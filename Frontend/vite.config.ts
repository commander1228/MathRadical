import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import tailwindcss from '@tailwindcss/vite'

// Vite only needs the Vue plugin; Tailwind is processed by PostCSS (postcss.config.js).
export default defineConfig({
  plugins: [vue(),tailwindcss()],
})
