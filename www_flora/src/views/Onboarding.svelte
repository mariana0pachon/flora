<script>
  export let goToNextView;
  export let skipToMap;
  export let currentView;
</script>

<div class="flex flex-col items-center justify-between min-h-screen py-8">
  <div class="text-center">
    <h1 class="text-2xl font-bold mb-4">Welcome</h1>
    <p class="mb-8">This is the {currentView} onboarding screen</p>
    <!-- Content goes here -->
  </div>
  
  <div class="w-full flex flex-col gap-4">
    <button 
      on:click={goToNextView}
      class="w-full py-3 bg-blue-500 text-white font-medium rounded-lg">
      Continue
    </button>
    <button 
      on:click={skipToMap}
      class="w-full py-2 text-blue-500">
      Skip to Map
    </button>
  </div>
</div>
