<script>
  import { createEventDispatcher } from 'svelte';
  import { fade } from 'svelte/transition'; // ✅ add this

  const dispatch = createEventDispatcher();

  let highlight = {
    what: false,
    map: false,
    contact: false,
  };

  function tempHighlight(key, action) {
    highlight[key] = true;
    setTimeout(() => {
      highlight[key] = false;
      action();
    }, 250);
  }

  function closeMenu() {
    dispatch('close');
  }

  function refreshPage() {
    window.location.reload();
  }

  function openContact() {
    window.open('https://linktr.ee/flora_electronic_garden', '_blank');
  }
</script>


<div
  transition:fade={{ duration: 300 }}
  class="fixed inset-0 z-50 bg-[#9E77ED]/90 text-white font-mono flex flex-col p-5 bg-cover bg-center backdrop-blur"
>
  <!-- Header -->
  <div class="flex justify-between items-center">
    <img
      src="/assets/header/logo_blanco.png"
      alt="Logo"
      class="h-[40px] cursor-pointer transition-colors duration-300"
      on:click={() => tempHighlight('what', refreshPage)}
      style="color: {highlight.what ? '#FEF377' : ''}"
    />

    <button
      class="text-4xl font-bold bg-transparent border-none cursor-pointer transition-colors duration-300"
      on:click={() => tempHighlight('map', closeMenu)}
      style="color: {highlight.map ? '#FEF377' : ''}"
      aria-label="Close"
    >
      ×
    </button>
  </div>

  <!-- Centered Links -->
  <div class="flex-1 flex flex-col justify-center items-center gap-8 text-3xl text-center">
    <a
      href="#"
      class="hover:opacity-80 transition-colors duration-300"
      on:click|preventDefault={() => tempHighlight('what', refreshPage)}
      style="color: {highlight.what ? '#FEF377' : ''}"
    >
      What is Flora?
    </a>

    <a
      href="#"
      class="hover:opacity-80 transition-colors duration-300"
      on:click|preventDefault={() => tempHighlight('map', closeMenu)}
      style="color: {highlight.map ? '#FEF377' : ''}"
    >
      Map
    </a>

    <a
      href="#"
      class="hover:opacity-80 transition-colors duration-300"
      on:click|preventDefault={() => tempHighlight('contact', openContact)}
      style="color: {highlight.contact ? '#FEF377' : ''}"
    >
      Contact us
    </a>
  </div>
</div>
