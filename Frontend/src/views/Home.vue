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
        
        <ToolCard
          title="Least Common Multiple (LCM)"
          description="Calculate the smallest positive integer that is divisible by both of your selected numbers. Useful for finding common denominators in fractions."
          routeName="lcm"
          buttonText="Try LCM"
          buttonClass="btn-primary"
        />

        <ToolCard
          title="Greatest Common Denominator (GCD)"
          description="Find the largest positive integer that divides each of the integers. Essential for simplifying fractions and number theory problems."
          routeName="gcd"
          buttonText="Try GCD"
          buttonClass="btn-secondary"
        />

      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import ToolCard from '../components/ToolCard.vue';
</script>