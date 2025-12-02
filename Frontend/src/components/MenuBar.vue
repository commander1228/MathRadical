<template>
<div class="navbar bg-base-300 shadow-sm">
  <router-link :to ="{ name: 'home'}" class="btn btn-ghost text-xl">Home</router-link> 


  <button class="btn" popovertarget="popover-1" style="anchor-name:--anchor-1">
  Utilities
</button>
<ul class="dropdown menu w-52 rounded-box bg-base-100 shadow-sm"
  popover id="popover-1" style="position-anchor:--anchor-1">
  <li><router-link :to="{ name: 'lcm' }">Least Common Multiple</router-link></li>
  <li><router-link :to="{ name: 'gcd' }">Greatest Common Denominator</router-link></li>
</ul>


</div>
</template>



<script setup lang="ts">

</script>