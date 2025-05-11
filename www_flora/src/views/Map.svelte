<script>
  import Header from '../components/Header.svelte';
  import InstructionCard from '../components/InstructionCard.svelte';
  import { fade } from 'svelte/transition';

  // State to track which card is open
  let activeCard = null;

  // State to track if the instruction modal should be shown
  let showModal = true;

  // Function to close the instruction modal
  function closeModal() {
    showModal = false;
  }

  // Card data for each icon
  const cardData = {
    semilla: {
      title: "SEED",
      illustration: "/assets/cards/semilla.png",
      roleTitle: "Beginning of the cycle",
      roleText: "The seed holds incredible power within its tiny shell. It contains all the knowledge to bring the garden back to life.",
      objective: "Find a place with soil and helping hands to begin growing.",
      bgColor: "bg-[#1D0405]"
    },
    caracol: {
      title: "SNAIL",
      illustration: "/assets/cards/caracol.png",
      roleTitle: "The lost traveler",
      roleText: "The giant snail has lost its shell—its home—and is now stranded in the middle of the dry riverbed.",
      objective: "Help the snail rebuild its path back home and call upon the ancient rocks for guidance.",
      bgColor: "bg-[#713C9F]"
    },
    abeja: {
      title: "BEES",
      illustration: "/assets/cards/abejas.png",
      roleTitle: "The loyal lovers",
      roleText: "Bees share an eternal bond with the garden’s flowers, dancing in circles to pollinate them. But now, they can no longer fly.",
      objective: "Find the missing piece that will allow them to reunite with their beloved flowers.",
      bgColor: "bg-[#2661CA]"
    }
  };

  // Function to open a specific card
  function openCard(cardId) {
    activeCard = cardId;
  }

  // Function to close the active card
  function closeCard() {
    activeCard = null;
  }
</script>

<div class="relative flex flex-col min-h-screen w-full bg-[#01281B] overflow-hidden">
  <Header />
  <!-- Map Container with Centered Content -->
  <div class="relative w-full flex-grow flex items-center justify-center">
    <!-- Map Image Full Width, Auto Height -->
    <div class="relative w-full">
      <img 
        src="/assets/mapa/mapa.png" 
        alt="Mapa" 
        class="w-full h-auto object-cover" 
      />
      <!-- Icons Positioned Relative to the Image with Numbers -->
      <div class="absolute top-50 left-5 cursor-pointer" on:click={() => openCard('abeja')}>
        <div class="relative">
          <img 
            src="/assets/mapa/abeja_icono.png"
            alt="Abeja Icon"
            class="w-25 h-auto hover:scale-110 transition-transform" 
          />
        </div>
      </div>
      
      <div class="absolute top-55 right-10 cursor-pointer" on:click={() => openCard('caracol')}>
        <div class="relative">
          <img 
            src="/assets/mapa/caracol_icono.png"
            alt="Caracol Icon"
            class="w-25 h-auto drop-shadow-lg hover:scale-110 transition-transform" 
          />
        </div>
      </div>
      
      <div class="absolute top-5 left-60 transform -translate-x-1/2 cursor-pointer" on:click={() => openCard('semilla')}>
        <div class="relative">
          <img 
            src="/assets/mapa/semilla_icono.png"
            alt="Semilla Icon"
            class="w-25 h-auto drop-shadow-lg hover:scale-110 transition-transform" 
          />
        </div>
      </div>
    </div>
  </div>

  <!-- Full Screen Card Modal -->
  {#if activeCard}
    <div transition:fade={{duration: 300}}>
      <InstructionCard
        bgColor={cardData[activeCard].bgColor}
        illustration={cardData[activeCard].illustration}
        title={cardData[activeCard].title}
        roleTitle={cardData[activeCard].roleTitle}
        roleText={cardData[activeCard].roleText}
        objective={cardData[activeCard].objective}
        onClose={closeCard}
      />
    </div>
  {/if}

  <!-- Grey Background when Modal is Shown -->
  {#if showModal}
    <div transition:fade={{duration: 300}} class="absolute top-0 left-0 w-full h-full bg-gray-500 opacity-50 z-40"></div>
  {/if}

  {#if showModal}
    <div transition:fade={{duration: 300}} class="absolute top-1/2 left-1/2 transform -translate-x-1/2 -translate-y-1/2 z-50 font-mono">
      <div class="bg-[#9E77ED] text-white rounded-lg p-4 shadow-lg">
        <p class="mb-4">Click on each numbered beast in sequence to uncover the tasks displayed on the board.</p>
        <button 
          on:click={closeModal}
          class="bg-white text-[#9E77ED] font-bold py-2 px-4 rounded hover:bg-gray-100 transition-colors w-full"
        >
          GOT IT!
        </button>
      </div>
    </div>
  {/if}
</div>
