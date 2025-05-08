<script>
  import Header from '../components/Header.svelte';
</script>

<div class="relative flex flex-col w-full h-full bg-[#01281B] overflow-hidden">
  <Header />

  <!-- Map Container with Auto Height Based on Image -->
  <div class="relative w-full">
    <!-- Map Image Full Width, Auto Height -->
    <img 
      src="/assets/mapa/mapa.png" 
      alt="Mapa" 
      class="w-full h-auto object-cover" 
    />

    <!-- Icons Positioned Relative to the Image -->
    <img 
      src="/assets/mapa/abeja_icono.png"
      alt="Abeja Icon"
      class="absolute top-10 left-8 w-10 h-10 animate-pulse drop-shadow-lg" 
    />
    <img 
      src="/assets/mapa/caracol_icono.png"
      alt="Caracol Icon"
      class="absolute top-16 right-10 w-10 h-10 animate-pulse drop-shadow-lg" 
    />
    <img 
      src="/assets/mapa/semilla_icono.png"
      alt="Semilla Icon"
      class="absolute top-24 left-1/2 transform -translate-x-1/2 w-10 h-10 animate-pulse drop-shadow-lg" 
    />
  </div>
</div>
