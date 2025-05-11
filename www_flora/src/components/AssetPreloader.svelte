<script>
  import { onMount } from 'svelte';

  export let onLoaded;

  const assetsToPreload = [
    '/assets/portada.png',
    '/assets/buttons/enter.png',
    '/assets/onboarding/onboarding1/bg_a.png',
    '/assets/onboarding/onboarding1/bg_b.png',
    '/assets/onboarding/onboarding1/il.png',
    '/assets/onboarding/onboarding2/bg_a.png',
    '/assets/onboarding/onboarding2/bg_b.png',
    '/assets/onboarding/onboarding2/il.png',
    '/assets/onboarding/onboarding3/bg_a.png',
    '/assets/onboarding/onboarding3/bg_b.png',
    '/assets/onboarding/onboarding3/il.png',
    '/assets/onboarding/recommendations.png',
    '/assets/buttons/okay.png',
    '/assets/mapa/mapa.png',
    '/assets/mapa/abeja_icono.png',
    '/assets/mapa/caracol_icono.png',
    '/assets/mapa/semilla_icono.png',
    '/assets/cards/semilla.png',
    '/assets/cards/caracol.png',
    '/assets/cards/abejas.png',
    '/assets/header/logo.png',
    '/assets/header/logo_blanco.png',
    '/assets/header/menu_icon.png',
    '/assets/buttons/arrow.png',
    '/assets/buttons/close.png',
  ];

  let loadedCount = 0;
  let totalAssets = assetsToPreload.length;
  let loading = true;

  onMount(() => {
    let promises = assetsToPreload.map(asset => {
      return new Promise((resolve, reject) => {
        const img = new Image();
        img.onload = () => {
          loadedCount++;
          resolve();
        };
        img.onerror = reject;
        img.src = asset;
      });
    });

    Promise.all(promises)
      .then(() => {
        loading = false;
        if (onLoaded) {
          onLoaded();
        }
      })
      .catch(error => {
        console.error('Error preloading assets:', error);
        loading = false; // Still hide loading even on error
        if (onLoaded) {
          onLoaded();
        }
      });
  });
</script>

{#if loading}
  <div class="fixed inset-0 flex items-center justify-center bg-gray-900 text-white text-xl z-50">
    Loading assets... ({loadedCount} / {totalAssets})
  </div>
{/if}
