<template>
  <div class="min-h-screen bg-base-200">
    <!-- Hero Section -->
    <div class="hero py-10 bg-base-100">
      <div class="hero-content text-center">
        <div class="max-w-md">
          <h1 class="text-5xl font-bold">ITS TIME TO MATH</h1>
          <p class="py-6">
            Welcome to MathRadical, your go-to suite for mathematical utilities. 
            Simplify your calculations with our easy-to-use tools designed for students and professionals alike.
          </p>
        </div>
      </div>
    </div>

    <!-- Tools Overview Section -->
    <div class="container mx-auto px-4 py-10">
      <h2 class="text-3xl font-bold text-center mb-8">Our Tools</h2>
      <div class="grid grid-cols-1 md:grid-cols-2 gap-6 max-w-4xl mx-auto">
        
        <!-- LCM Card -->
        <div class="card bg-base-100 shadow-xl hover:shadow-2xl transition-shadow">
          <div class="card-body">
            <h2 class="card-title">Least Common Multiple (LCM)</h2>
            <p>
              Calculate the smallest positive integer that is divisible by both of your selected numbers. 
              Useful for finding common denominators in fractions.
            </p>
            <div class="card-actions justify-end mt-4">
              <router-link :to="{ name: 'lcm' }" class="btn btn-primary">Try LCM</router-link>
            </div>
          </div>
        </div>

        <!-- GCD Card -->
        <div class="card bg-base-100 shadow-xl hover:shadow-2xl transition-shadow">
          <div class="card-body">
            <h2 class="card-title">Greatest Common Denominator (GCD)</h2>
            <p>
              Find the largest positive integer that divides each of the integers. 
              Essential for simplifying fractions and number theory problems.
            </p>
            <div class="card-actions justify-end mt-4">
              <router-link :to="{ name: 'gcd' }" class="btn btn-secondary">Try GCD</router-link>
            </div>
          </div>
        </div>

      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
</script>