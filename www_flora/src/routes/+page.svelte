<script>
  import Onboarding from '../views/Onboarding.svelte';
  import Recommendation from '../views/Recommendation.svelte';
  import Map from '../views/Map.svelte';
  import Landing from '../views/Landing.svelte';

  // State to track current view
  let currentView = 'onboarding1';

  // Navigation functions
  function goToNextView() {
    switch (currentView) {
      case 'landing':
        currentView = 'landing';
        break;
      case 'onboarding1':
        currentView = 'onboarding2';
        break;
      case 'onboarding2':
        currentView = 'onboarding3';
        break;
      case 'onboarding3':
        currentView = 'recommendation';
        break;
      case 'recommendation':
        currentView = 'map';
        break;
      default:
        break;
    }
  }

  function skipToMap() {
    currentView = 'map';
  }
</script>

<main class="min-h-screen bg-gray-100 text-gray-900">
    {#if currentView === 'landing'}
      <Landing {goToNextView}/>
    {:else if currentView === 'onboarding1'}
      <Onboarding {goToNextView} {skipToMap} {currentView} />
    {:else if currentView === 'onboarding2'}
      <Onboarding {goToNextView} {skipToMap} {currentView}/>
    {:else if currentView === 'onboarding3'}
      <Onboarding {goToNextView} {skipToMap} {currentView} />
    {:else if currentView === 'recommendation'}
      <Recommendation {goToNextView}  {skipToMap}/>
    {:else if currentView === 'map'}
      <Map />
    {/if}
</main>

<style global>
  /* Mobile-only styles */
  @media (min-width: 640px) {
    body::before {
      content: "This app is designed for mobile devices only";
      position: fixed;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      display: flex;
      align-items: center;
      justify-content: center;
      background-color: white;
      z-index: 9999;
      padding: 2rem;
      font-size: 1.5rem;
      text-align: center;
    }
  }
</style>
