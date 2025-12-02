import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/Home.vue'
import LeastCommonMultiple from '../views/LeastCommonMultiple.vue'
import GreatestCommonDenominator from '../views/GreatestCommonDenominator.vue'

const routes = [
  {path: '/', name: 'home', component: Home },
  {path:'/leastcommonmultiple',name: 'lcm', component: LeastCommonMultiple },
  {path:'/greatestcommondenominator',name: 'gcd', component: GreatestCommonDenominator },
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
