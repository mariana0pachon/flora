<script>
  export let goToNextView;
  import Button from '../components/Button.svelte';
</script>

<div class="bg-[#01281B] flex flex-col items-center justify-between min-h-screen w-full relative">
  <!-- Full-screen background image -->
  <img 
    src="/assets/portada.png"
    alt="Landing Page Cover"
    class="absolute inset-0 w-full h-full object-cover"
  />

  <!-- Button positioned at the bottom of the screen -->
  <div class="w-full flex justify-center absolute bottom-22 z-10">
    <button on:click={goToNextView} class="focus:outline-none">
      <Button text="LET'S ENTER"/>
    </button>
  </div>
</div>
