<script>
  import { onMount } from 'svelte';
  import { fade } from 'svelte/transition';
  import Onboarding from '../views/Onboarding.svelte';
  import Recommendation from '../views/Recommendation.svelte';
  import Map from '../views/Map.svelte';
  import Landing from '../views/Landing.svelte';
  import AssetPreloader from '../components/AssetPreloader.svelte';

  // State to track current view
  let currentView = 'landing';
  let isMobile = false;
  let assetsLoaded = false;

  function handleAssetsLoaded() {
    assetsLoaded = true;
  }

  // Navigation functions
  function goToNextView() {
    switch (currentView) {
      case 'landing':
        currentView = 'onboarding1';
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

  onMount(() => {
    // Check if we're in the browser and it's not a mobile screen
    if (typeof window !== 'undefined') {
      isMobile = window.innerWidth <= 640;

      // Request fullscreen if not on mobile
      if (!isMobile) {
        requestFullscreen();
      }
    }
  });

  // Function to enter fullscreen
  function requestFullscreen() {
    let elem = document.documentElement;
    if (elem.requestFullscreen) {
      elem.requestFullscreen();
    } else if (elem.mozRequestFullScreen) { // Firefox
      elem.mozRequestFullScreen();
    } else if (elem.webkitRequestFullscreen) { // Chrome/Safari/Opera
      elem.webkitRequestFullscreen();
    } else if (elem.msRequestFullscreen) { // IE/Edge
      elem.msRequestFullscreen();
    }
  }
</script>

{#if !assetsLoaded}
  <AssetPreloader onLoaded={handleAssetsLoaded} />
{:else}
  <main>
      {#if currentView === 'landing'}
        <div transition:fade>
          <Landing {goToNextView}/>
        </div>
      {:else if currentView === 'onboarding1'}
        <div transition:fade>
          <Onboarding {goToNextView} {skipToMap} {currentView} />
        </div>
      {:else if currentView === 'onboarding2'}
        <div transition:fade>
          <Onboarding {goToNextView} {skipToMap} {currentView}/>
        </div>
      {:else if currentView === 'onboarding3'}
        <div transition:fade>
          <Onboarding {goToNextView} {skipToMap} {currentView} />
        </div>
      {:else if currentView === 'recommendation'}
        <div transition:fade>
          <Recommendation {goToNextView}  {skipToMap}/>
        </div>
      {:else if currentView === 'map'}
        <div transition:fade>
          <Map />
        </div>
      {/if}
  </main>
{/if}

{#if !isMobile}
  <div class="not-mobile-message">
    This app is designed for mobile devices only
  </div>
{/if}

<style global>
  /* Mobile-only styles */
  @media (min-width: 640px) {
    .not-mobile-message {
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
