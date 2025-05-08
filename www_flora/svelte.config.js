import adapter from '@sveltejs/adapter-static';

export default {
  kit: {
    adapter: adapter({
      pages: 'build',
      assets: 'build',
      fallback: 'index.html' // Optional: use for SPA behavior
    }),
    paths: {
      base: '', // optional: set base path if you're deploying to a subfolder
    },
  }
};
